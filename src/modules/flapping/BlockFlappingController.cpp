/****************************************************************************
 *
 *   Copyright (c) 2014 PX4 Development Team. All rights reserved.
 *   Author: James Goppert, Ben Perseghetti, Scott Yantek
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#include "BlockFlappingController.hpp"

void BlockFlappingController::update() {
	// wait for a estimator update or exit at 100 Hz 
	// running twice as fast as pwm (50 Hz) to avoid lag issues
	if (poll(&_attPoll, 1, 1) < 0) return; // poll error

	uint64_t newTimeStamp = hrt_absolute_time();
	float dt = (newTimeStamp - _timeStamp) / 1.0e6f;
	_timeStamp = newTimeStamp;

	// check for sane values of dt
	// to prevent large control responses
	if (dt > 1.0f || dt < 0) return;

	// set dt for all child blocks
	setDt(dt);

	// check for new updates
	if (_param_update.updated()) {
		updateParams();
		_ga.setMutateProb(_mutateProb.get());
		_ga.setReproducingRatio(_reproducingRatio.get());
	}

	// get new information from subscriptions
	updateSubscriptions();

	// default all output to zero unless handled by mode
	for (unsigned i = 2; i < NUM_ACTUATOR_CONTROLS; i++) {
		_actuators.control[i] = 0.0f;
	}

	// default controls
	float elevator = 0.0f;
	float aileron = 0.0f;
	float throttle = 0.0f;
	float kOmega = 0.0f;

	// handle autopilot modes and learning
	//learning over roll and pitch
	if (_status.main_state == MAIN_STATE_ALTCTL) {//ALTCTL = learning mode
		// do flapping learning
		if (_learnFlapping.get() > 0) {
			throttle = 0.201f + 0.8f*_ga.getTestNorm(0);
			kOmega = 2.0f*(_ga.getTestNorm(1) - 0.5f);
			//printf("doing learn flap: throttle %4.2f, kOmega %4.2f\n", double(throttle), double(kOmega));
			if (! _currentlyEvaluating) { //no genome is being evaluated: get new one to test
				//initilize learning time
				_learnStart = hrt_absolute_time();
				_currentlyEvaluating = true;
			} else if ((hrt_absolute_time() - _learnStart) > _lrnTime.get()) { //current genome test is at its end
				// we are storing the fitness in the vicon
				// packet since it is setup to send
				// from the groundcontrol
				
				// powaer
				float powerAvg = _powerSum/_powerCount;
				_powerCount = 0;
				_powerSum = 0;
				printf("P: %4.2f, ", double(powerAvg));

				// fitness
				float fitness = - 0.05f*powerAvg
					+ _vicon.z
					-_vicon.x;
				_ga.reportFitness(fitness);
				_ga.nextTest();
				_currentlyEvaluating = false;
			}
		// do glide learning
		} else {
			kOmega = _kOmega.get();
			float aileronLearn = _ga.getTestNorm(0);
			float elevatorLearn = _ga.getTestNorm(1);
			//get elevator and aileron command from learning
			aileron = (_ailMin.get() + _ailRange.get() * aileronLearn)/_servoTravel.get();
			elevator = (_elevMin.get() + _elevRange.get() * elevatorLearn)/_servoTravel.get();
			if (! _currentlyEvaluating) { //no genome is being evaluated: get new one to test
				//initilize learning time
				_learnStart = hrt_absolute_time();
				_currentlyEvaluating = true;
			} else if ((hrt_absolute_time() - _learnStart) > _lrnTime.get()) { //current genome test is at its end

				// we are storing the fitness in the vicon
				// packet since it is setup to send
				// from the groundcontrol
				float fitness =
					-(_vicon.z/_vicon.x)
					- fabsf(_vicon.y)
					- 1.0f*(0.01f*fabsf(_vicon.roll)
						+ 2.0f*fabsf(_vicon.pitch - 12.0f)
						+ 2.0f*fabsf(_vicon.yaw));
				_ga.reportFitness(fitness);
				_ga.nextTest();
				_currentlyEvaluating = false;
			}
		}
	} else if (_status.main_state == MAIN_STATE_MANUAL) {
		elevator = _manual.x;
		aileron = _manual.y;
		throttle = _manual.z;
		kOmega = _manual.r;
	} else if (_status.main_state == MAIN_STATE_AUTO_MISSION) {
	} else if (_status.main_state == MAIN_STATE_AUTO_RTL) {
	} else if (_status.main_state == MAIN_STATE_AUTO_LOITER) {
	} else if (_status.main_state == MAIN_STATE_POSCTL) {
	} else {
	}

	// flapping cycle function
	float wingLeft = 0;
	float wingRight = 0;
	flappingFunction(dt, aileron, elevator, throttle, kOmega, wingLeft, wingRight);

	// keep track of average power
	float power = _batteryStatus.current_a*_batteryStatus.voltage_v;
	_powerCount++;
	_powerSum += power;

	// actuators
	_actuators.timestamp = _timeStamp;
	_actuators.control[CH_LEFT] = _wingLeftLowPass.update(wingLeft);
	_actuators.control[CH_RIGHT] = _wingRightLowPass.update(wingRight);

	// update all publications
	updatePublications();
}

void BlockFlappingController::flappingFunction(
		float dt,
		float aileron,
		float elevator, float throttle,
		float kOmega,
		float & wingLeft, float & wingRight) {
	// function parameters
	float servoTravel = _servoTravel.get();
	float wingUp = _wingUp.get()/servoTravel;
	float wingDown = _wingDown.get()/servoTravel;
	float wingGlide = _wingGlide.get()/servoTravel;
	//float tDown2Up = _tDown2Up.get();
	//float tUp2Glide = _tUp2Glide.get();
	float throttleGlide = _throttleGlide.get();
	float freq = _minFrequency.get() + _throttle2Frequency.get()*throttle;
	float ampl = wingUp - wingDown;
	float omega = 2*M_PI_F*freq;

	// compute flap
	if (throttle >= throttleGlide) {
		// up stroke
		if (_wingFlapState > M_PI_F/2 && _wingFlapState < 3*M_PI_F/2) {
			if (kOmega > 0) {
				_wingFlapState += omega*dt;
			} else {
				_wingFlapState += (1-kOmega)*omega*dt;
			}
		// down stroke
		} else {
			if (kOmega > 0) {
				_wingFlapState += (1+kOmega)*omega*dt;
			} else {
				_wingFlapState += omega*dt;
			}
		}
	} else {
		float closeFactor = 1.5;
		float safeFreq = 0.5; // Hz
		float dy = fabs(sinf(closeFactor*2*M_PI_F*safeFreq*dt));
		float y = sinf(_wingFlapState);
		// you are close enough, stop flapping
		if (fabsf(y) < dy) {
			_wingFlapState = 0;
		// otherwise  continue flap until close enough
		} else {
			_wingFlapState += 2*M_PI_F*safeFreq*dt;
		}
	}
	
	// wrap wing flap state
	while (_wingFlapState  > 2*M_PI_F) _wingFlapState -= 2*M_PI_F;

	// mixing
	float flap = ampl*sinf(_wingFlapState);
	wingLeft = aileron - elevator + flap + wingGlide;
	wingRight = -aileron - elevator + flap + wingGlide;
}

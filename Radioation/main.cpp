#include<iostream>
#include<cstdlib>
#include "gtest/gtest.h"
#include "gmock/gmock.h" 



class RadiationSensor {
public:
	virtual float alpha_radiation() = 0;
	virtual float beta_radiation() = 0;
	virtual float gamma_radiation() = 0;
};

class Terminal {
public:
	void display(std::string output) {
		std::cout << ">> " << output << std::endl;
	}
};
class Buzzer {
public:
	void alarm() {
		std::cout << "\a";
		std::cout << "  ioioio :)  ";
	}
};

class Detector {
	RadiationSensor& sensor;
	Buzzer& buzzer;
	Terminal& terminal;
public:
	Detector(RadiationSensor& sensor,
		Buzzer& buzzer,
		Terminal& terminal) : sensor(sensor), buzzer(buzzer), terminal(terminal) {
		this->sensor = sensor;
		this->buzzer = buzzer;
		this->terminal = terminal;
	}
	bool check() {
		
		if (sensor.alpha_radiation() > 1) {
			buzzer.alarm();
			terminal.display("too high alpha radiation");
		}
		
		if (sensor.beta_radiation() > 1) {
			buzzer.alarm();
			terminal.display("too high beta radiation");
		}
		if (sensor.gamma_radiation() > 1) {
			buzzer.alarm();
			terminal.display("too high gamma radiation");
		}
		return sensor.alpha_radiation() > 1 || sensor.beta_radiation() > 1 || sensor.gamma_radiation() > 1;
	}
};


class MockSensor : public RadiationSensor {
public:
	MOCK_METHOD(float, alpha_radiation, (), (override));
	MOCK_METHOD(float, beta_radiation, (), (override));
	MOCK_METHOD(float, gamma_radiation, (), (override));
};

int main() {
	MockSensor sensor;
	Buzzer buzzer;
	Terminal terminal;
	Detector detector2000(sensor, buzzer, terminal);


	bool isAirGood = detector2000.check();


	return 0;
}


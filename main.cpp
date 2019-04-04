// Jake Wright	CSI-370-02
// Final Project
// Sinewave Piano
// * computations done via in-line assembly FPU operations *
// * orignial computations done in C++ commented out to
//	 better understand/remember what each computation is doing *

#include <iostream>
#include <Windows.h>
#include <string>
#include <SFML/Audio.hpp>

const int N_SAMPLES = 44100;
const int SAMPLE_RATE = 44100;

class SineWave {
public:
	SineWave(float freq) {
		// constructor
		setAmplitude(30000); //default amplitude (loudness)
		setTone(freq);
	}

	float computeTick(float time, float freq) {
		// compute value of each sample based on tone frequency
		float result, tpc, cycles, rad = 0.0;
		float rate = float(SAMPLE_RATE);
		float ampl = amplitude;

		__asm {finit
			fld freq
			fld rate
			fdiv st(0), st(1)
			fstp tpc

			fld tpc
			fld time
			fdiv st(0), st(1)
			fstp cycles

			fld1
			fld1
			fadd st(0), st(1)
			fldpi
			fmulp st(1), st(0)
			fld cycles
			fmul st(0), st(1)
			fstp rad

			fld rad
			fsin
			fld ampl
			fmul st(0), st(1)
			fstp result
		};

		//tpc = SAMPLE_RATE / freq;
		//cycles = time / tpc;
		//rad = 2 * M_PI * cycles;
		//result = amplitude * sin(rad);
		this->canPlay = true;

		return result;
	}

	void setTone(float freq) {
		//std::cout << "setting tone" << std::endl;
		for (unsigned i = 0; i < N_SAMPLES; i++) {
			samples[i] = computeTick(i, freq);
		}
		//std::cout << "computed ticks" << std::endl;

		if (!buffer.loadFromSamples(samples, N_SAMPLES, 1, SAMPLE_RATE)) {
			std::cout << "LOADING FAILED :(" << std::endl;
		}
		sound.setBuffer(buffer);
	}

	void setAmplitude(float amp) {
		this->amplitude = amp;
	}

	bool getIsPlaying() {
		return this->isPlaying;
	}

	void playTone() {
		if (!this->isPlaying) {
			this->isPlaying = true;
			if (this->canPlay) {
				sound.setLoop(true);
				sound.play();
			}
		}
	}

	void stopTone() {
		if (this->isPlaying) {
			this->isPlaying = false;
			sound.stop();
			sound.setLoop(false);
		}
	}

private:
	sf::SoundBuffer buffer;
	sf::Sound sound;
	sf::Int16 samples[N_SAMPLES];
	bool canPlay;
	float amplitude;
	bool isPlaying = false;
};


void createPiano(SineWave *pianoKeys[13]) {
	float pitch = 262.0; // starting pitch for computations (note C4)
	float exponent = 1.0 / 12.0;

	for (int i = 0; i < 13; i++) {
		pianoKeys[i] = new SineWave(pitch);

		_asm {
			fld exponent
			f2xm1
			fld1
			fadd st(0), st(1)
			fld pitch
			fmul st(0), st(1)
			fstp pitch
		};

		pitch = floor(pitch);
		//pitch = floor(pow(2.0, exponent) * pitch);
	}
}

void deletePiano(SineWave *pianoKeys[13]) {
	for (int i = 0; i < 13; i++) {
		delete pianoKeys[i];
	}
}

void menuOutput() {
	std::cout << "PLAY PIANO" << std::endl;
	std::cout << "Press 'esc' key at any time to exit" << std::endl;
	std::cout << "___________________________________________________" << std::endl;
	std::cout << "____c#-2____d#-3________f#-5____g#-6____a#-7" << std::endl;
	std::cout << "///|    |//|    |////////|    |//|    |//|    |/////" << std::endl;
	std::cout << "///|    |//|    |////////|    |//|    |//|    |/////" << std::endl;
	std::cout << "///|    |//|    |////////|    |//|    |//|    |/////" << std::endl;
	std::cout << "///|____|//|____|////////|____|//|____|//|____|/////" << std::endl;
	std::cout << " c--Q____d--W____e--E__f--R____g--T____a--Y____c'-U" << std::endl;
	std::cout << "|    |//|    |//|    ||    |//|    |//|    |//|    |" << std::endl;
	std::cout << "|    |//|    |//|    ||    |//|    |//|    |//|    |" << std::endl;
	std::cout << "|    |//|    |//|    ||    |//|    |//|    |//|    |" << std::endl;
	std::cout << "|____|//|____|//|____||____|//|____|//|____|//|____|" << std::endl;
}

void playPiano(SineWave *pianoKeys[13]) {

	if (GetKeyState('Q') & 0x8000) {
		pianoKeys[0]->playTone();
	}
	else {
		pianoKeys[0]->stopTone();
	}

	if (GetKeyState('2') & 0x8000) {
		pianoKeys[1]->playTone();
	}
	else {
		pianoKeys[1]->stopTone();
	}

	if (GetKeyState('W') & 0x8000) {
		pianoKeys[2]->playTone();
	}
	else {
		pianoKeys[2]->stopTone();
	}

	if (GetKeyState('3') & 0x8000) {
		pianoKeys[3]->playTone();
	}
	else {
		pianoKeys[3]->stopTone();
	}

	if (GetKeyState('E') & 0x8000) {
		pianoKeys[4]->playTone();
	}
	else {
		pianoKeys[4]->stopTone();
	}

	if (GetKeyState('R') & 0x8000) {
		pianoKeys[5]->playTone();
	}
	else {
		pianoKeys[5]->stopTone();
	}

	if (GetKeyState('5') & 0x8000) {
		pianoKeys[6]->playTone();
	}
	else {
		pianoKeys[6]->stopTone();
	}

	if (GetKeyState('T') & 0x8000) {
		pianoKeys[7]->playTone();
	}
	else {
		pianoKeys[7]->stopTone();
	}

	if (GetKeyState('6') & 0x8000) {
		pianoKeys[8]->playTone();
	}
	else {
		pianoKeys[8]->stopTone();
	}

	if (GetKeyState('Y') & 0x8000) {
		pianoKeys[9]->playTone();
	}
	else {
		pianoKeys[9]->stopTone();
	}

	if (GetKeyState('7') & 0x8000) {
		pianoKeys[10]->playTone();
	}
	else {
		pianoKeys[10]->stopTone();
	}

	if (GetKeyState('U') & 0x8000) {
		pianoKeys[11]->playTone();
	}
	else {
		pianoKeys[11]->stopTone();
	}

	if (GetKeyState('I') & 0x8000) {
		pianoKeys[12]->playTone();
	}
	else {
		pianoKeys[12]->stopTone();
	}
}


int main() {
	SineWave *pianoKeys[13]; // initialize array for keys to be played
	std::string keyboardKeys = "Q2W3ER5T6Y7UI"; // string values cooresponding to keys that will produce a tone
	createPiano(pianoKeys); // populate array with 
	int index = 0;
	menuOutput();

	// active loop -- run program until user cancels with 'Esc' key
	while (1) {
		playPiano(pianoKeys);
		if (GetKeyState(keyboardKeys[index]) & 0x8000) {
			pianoKeys[index]->playTone();
		}
		else {
			pianoKeys[index]->stopTone();
		}
		index++;
		
		if (index > 12) {
			index = 0;
		}
		

		if (GetKeyState(VK_ESCAPE) & 0x8000) {
			break;
		}
	}

	deletePiano(pianoKeys);
	
	return 0;
}
from scipy.io.wavfile import write
import numpy as np
#import sounddevice as sd

def wav():
	# 48000 cycles/sec
	sample_rate = 48000
	# frequency, a-440 (cycles/sec)
	#f = 440
	f = 2225

	# evenly spaced numbers over specified interval
	t = np.linspace(0, 1, sample_rate, endpoint=False)

	# Amplitude: ¼ maximum possible 16-bit amplitude (values in the range -8192..8192)
	# 32,767 / 4 = 8192
	amplitude = np.iinfo(np.int16).max // 4

	# create sin wave mult by frequency (f) to get 440 cycles over 1 second time array (t)
	# multiply by amplitude scales to wave down 1/4
	data = amplitude * np.sin(2 * np.pi * f * t)

	# write() takes: filename, sample rate, and the array of samples
	write("test4.wav", sample_rate, data.astype(np.int16))

	return

def clipped():

	sample_rate = 48000
	f = 440

	t = np.linspace(0, 1, sample_rate, endpoint=False)

	amplitude = np.iinfo(np.int16).max // 2
	# creating the min/max amplitude to clip the wave at
	max = np.iinfo(np.int16).max // 4
	min = np.iinfo(np.int16).min // 4

	data = amplitude * np.sin(2 * np.pi * f * t)

	# clip limits the values in an array, Given an interval, i
	# values outside the interval are clipped to the interval edges
	clipped = np.clip(data, min, max)

	write("clipped.wav", sample_rate, clipped.astype(np.int16))

	# sounddevice plays back an array holding audio data with some sampling frequency
	sd.play(clipped.astype(np.int16), sample_rate)
	# block the Python interpreter until playback is finished with wait()
	sd.wait()

	return

if __name__ == "__main__":

	wav()

	#clipped()

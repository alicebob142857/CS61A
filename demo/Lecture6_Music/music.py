from ctypes import c_buffer
from wave import open
from struct import Struct
from math import floor

#设置帧数
frame_rate = 11025

def encode(x):
    """Encode float x between -1 and 1 as two bytes
    (See http://doxs.python.org/3/library/struct.html)
    """
    i = int(16384 * x)
    return Struct('h').pack(i)

def play(sampler, name='song.wav', seconds=2):
    """Write the output of a sampler function as a wav file.
    (See http://doxs.python.org/3/library/wave.html)
    """
    out = open(name, 'wb')
    out.setnchannels(1)
    out.setsampwidth(2)
    out.setframerate(frame_rate)
    t = 0
    while t < seconds * frame_rate:
        sample = sampler(t)
        out.writeframes(encode(sample))
        t += 1
    out.close()

def tri(frequency, amplitude=0.3):
    """Create a coninuous triangle wave"""
    #How many frame per period
    period = frame_rate // frequency
    def sampler(t):
        #t represent the t-th frame of the song, and return the height of the wave
        #floor function: round down
        ratio = (t / period - floor(t / period + 0.5)) * 4
        if ratio > 1:
            ratio = 2 - ratio
        return amplitude * ratio
    return sampler

c_freq, e_freq, g_freq = 261.63, 329.63, 392.00

def both(f, g):
    """ blend the frequency of two musical scale"""
    return lambda t: f(t) + g(t)

def note(f, start, end, fade=0.01):
    """modify the wave function"""
    def sampler(t):
        start_frame = start * frame_rate
        end_frame = end * frame_rate
        fade_frame = fade * frame_rate
        if t < start_frame:
            return 0
        elif t > end_frame:
            return 0
        #gradual change of the music
        elif t < fade_frame + start_frame:
            return (t - start_frame) / fade_frame * f(t)
        elif t > end_frame - fade_frame:
            return (end_frame - t) / fade_frame * f(t)
        else:
            return f(t)
    return sampler

def mario_at(octave):
    c, e = tri(octave * c_freq), tri(octave * e_freq)
    g, low_g = tri(octave * g_freq), tri(octave * g_freq / 2)
    return mario(c, e, g, low_g)

def mario(c, e, g, low_g):
    """ee0e0ce0g-00low_g-00"""
    #z is the flow of time~
    z = 0
    song = note(e, z, z + 1/8)
    z += 1/8
    song = both(song, note(e, z, z + 1/8))
    z += 1/4
    song = both(song, note(e, z, z + 1/8))
    z += 1/4
    song = both(song, note(c, z, z + 1/8))
    z += 1/8
    song = both(song, note(e, z, z + 1/8))
    z += 1/4
    song = both(song, note(g, z, z + 1/4))
    z += 1/2
    song = both(song, note(low_g, z, z + 1/4))
    z += 1/2
    return song

play(mario_at(1))


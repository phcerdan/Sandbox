import sys
try:
    from urllib.request import urlretrieve
except ImportError:
    from urllib import urlretrieve
import os
import itk

# Download data
file_name = 'cthead1.png'
if not os.path.exists(file_name):
    url = 'https://data.kitware.com/api/v1/file/57b5d9ef8d777f10f269538f/download'
    urlretrieve(url, file_name)
Dimension = 2
I = itk.Image[itk.F, Dimension]
reader = itk.ImageFileReader[I].New(FileName=file_name)
reader.Update()
image = reader.GetOutput()

padded = itk.FFTPadImageFilter.New(Input=image)
b = itk.ConstantBoundaryCondition[I]()
b.SetConstant(itk.NumericTraits.F.min())
padded.SetBoundaryCondition(b)
padded.Update()

ForwardFFTType = itk.ForwardFFTImageFilter.IF2ICF2
forwardFFT = ForwardFFTType.New(Input=padded)
forwardFFT.Update()
freqImage = forwardFFT.GetOutput()

WaveletType = itk.SimoncelliIsotropicWavelet.F2PD2
ForwardWaveletType = itk.WaveletFrequencyForwardUndecimated.ICF2ICF2SimoncelliF2PD2
levels = 2
highPassSubBands = 1
forwardWavelet = ForwardWaveletType.New(Input=freqImage)
forwardWavelet.SetLevels(levels)
forwardWavelet.SetHighPassSubBands(highPassSubBands)
forwardWavelet.Update()

outputs = forwardWavelet.GetOutputs()

InverseWaveletType = itk.WaveletFrequencyInverseUndecimated.ICF2ICF2SimoncelliF2PD2
inverseWavelet = InverseWaveletType.New()
inverseWavelet.SetLevels(levels)
inverseWavelet.SetHighPassSubBands(highPassSubBands)
# for i in range(forwardWavelet.GetNumberOfOutputs()):
#     inverseWavelet.SetInput(i, modifiedWavelets[i])
inverseWavelet.SetInputs(outputs) # This works after francois patch (9th April 2018)
inverseWavelet.Update()

inverseWaveletFFT = itk.InverseFFTImageFilter.New(Input=inverseWavelet.GetOutput())
inverseWaveletFFT.Update()


#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkWrapPadImageFilter.h"
#include "itkForwardFFTImageFilter.h"
#include "itkComplexToRealImageFilter.h"
#include "itkComplexToImaginaryImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"

int
main(int argc, char * argv[])
{
  if (argc != 4)
  {
    std::cerr << "Usage: " << std::endl;
    std::cerr << argv[0];
    std::cerr << " <InputFileName> <Real filename> <Imaginary filename>";
    std::cerr << std::endl;
    return EXIT_FAILURE;
  }

  const char * inputFileName = argv[1];
  const char * realFileName = argv[2];
  const char * imaginaryFileName = argv[3];

  constexpr unsigned int Dimension = 3;

  using FloatPixelType = float;
  using FloatImageType = itk::Image<FloatPixelType, Dimension>;

  using ReaderType = itk::ImageFileReader<FloatImageType>;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName(inputFileName);

  using UnsignedCharPixelType = unsigned char;
  using UnsignedCharImageType = itk::Image<UnsignedCharPixelType, Dimension>;

  // Some FFT filter implementations, like VNL's, need the image size to be a
  // multiple of small prime numbers.
  // TODO: This padding is not the FFT pad
  // using PadFilterType = itk::WrapPadImageFilter<FloatImageType, FloatImageType>;
  // PadFilterType::Pointer padFilter = PadFilterType::New();
  // padFilter->SetInput(reader->GetOutput());
  // PadFilterType::SizeType padding;
  //
  // padding[0] = 0;
  // padding[1] = 0;
  // padding[2] = 0;
  // padFilter->SetPadUpperBound(padding);

  using FFTType = itk::ForwardFFTImageFilter<FloatImageType>;
  FFTType::Pointer fftFilter = FFTType::New();
  // fftFilter->SetInput(padFilter->GetOutput());
  fftFilter->SetInput(reader->GetOutput());

  using FFTOutputImageType = FFTType::OutputImageType;

  // Extract the real part
  using RealFilterType = itk::ComplexToRealImageFilter<FFTOutputImageType, FloatImageType>;
  RealFilterType::Pointer realFilter = RealFilterType::New();
  realFilter->SetInput(fftFilter->GetOutput());


  using WriterType = itk::ImageFileWriter<FloatImageType>;
  WriterType::Pointer realWriter = WriterType::New();
  realWriter->SetFileName(realFileName);
  realWriter->SetInput(realFilter->GetOutput());
  try
  {
    realWriter->Update();
  }
  catch (itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  // Extract the imaginary part
  using ImaginaryFilterType = itk::ComplexToImaginaryImageFilter<FFTOutputImageType, FloatImageType>;
  ImaginaryFilterType::Pointer imaginaryFilter = ImaginaryFilterType::New();
  imaginaryFilter->SetInput(fftFilter->GetOutput());

  WriterType::Pointer complexWriter = WriterType::New();
  complexWriter->SetFileName(imaginaryFileName);
  complexWriter->SetInput(imaginaryFilter->GetOutput());
  try
  {
    complexWriter->Update();
  }
  catch (itk::ExceptionObject & error)
  {
    std::cerr << "Error: " << error << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

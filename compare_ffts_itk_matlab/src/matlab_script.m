in_string = 'tinyCylinder'
in_img = strcat(in_string, '.nii')
real_img = strcat('fftReal_untouch_',in_img)
imag_img = strcat('fftImag_untouch_',in_img)
out_path = '/tmp/'
data = load_untouch_nii(in_img);
fftImg = fftn(data.img);
fftReal = real(fftImg)
fftImag = imag(fftImg)

realPart = make_nii(fftReal);
imagPart = make_nii(fftImag);
save_nii(realPart, strcat(out_path, real_img));
save_nii(imagPart, strcat(out_path, imag_img));
% flip_lrtd('fftRealPart.nii",“fftRealPart_flipped_lrtd”);
% flip_lrtd('fftImagPart.nii",“fftImagPart_flipped_lrtd”);



% Load ITK img:
itk_fftReal = load_nii('/tmp/itk_fftReal_tinyCylinder.nii')

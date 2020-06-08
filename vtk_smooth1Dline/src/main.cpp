// From https://vtk.org/Wiki/VTK/Examples/Cxx/PolyData/ParametricSpline
#include <vtkSmartPointer.h>
#include <vtkCellArray.h>
#include <vtkCellData.h>
#include <vtkDoubleArray.h>
#include <vtkPoints.h>
#include <vtkParametricSpline.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkParametricFunctionSource.h>

int main(int, char *[])
{
  // This is an edge from airway.nrrd. edges[290]
  // Create points.
  double source[3] = {152, 174, 296};
  double target[3] = {139, 176, 289};
  double p0[3] = {151, 175, 296};
  double p1[3] = {150, 175, 296};
  double p2[3] = {149, 175, 295};
  double p3[3] = {148, 174, 294};
  double p4[3] = {147, 175, 294};
  double p5[3] = {146, 175, 293};
  double p6[3] = {145, 175, 292};
  double p7[3] = {144, 175, 292};
  double p8[3] = {143, 175, 291};
  double p9[3] = {142, 175, 291};
  double p10[3] = {141, 175, 290};
  double p11[3] = {140, 176, 290};

  // Create a vtkPoints object and store the points in it
  vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
  points->InsertNextPoint(source);
  points->InsertNextPoint(p0);
  points->InsertNextPoint(p1);
  points->InsertNextPoint(p2);
  points->InsertNextPoint(p3);
  points->InsertNextPoint(p4);
  points->InsertNextPoint(p5);
  points->InsertNextPoint(p6);
  points->InsertNextPoint(p7);
  points->InsertNextPoint(p8);
  points->InsertNextPoint(p9);
  points->InsertNextPoint(p10);
  points->InsertNextPoint(p11);
  points->InsertNextPoint(target);

  vtkSmartPointer<vtkParametricSpline> spline =
    vtkSmartPointer<vtkParametricSpline>::New();
  spline->SetPoints(points);

  vtkSmartPointer<vtkParametricFunctionSource> functionSource =
    vtkSmartPointer<vtkParametricFunctionSource>::New();
  functionSource->SetParametricFunction(spline);
  functionSource->Update();
  // const int resolution = 1000;
  // functionSource->SetUResolution(resolution);
  // functionSource->SetVResolution(resolution);
  // functionSource->SetWResolution(resolution);
  functionSource->Print(std::cout);

  // Setup actor and mapper
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(functionSource->GetOutputPort());

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  // Setup render window, renderer, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderer->AddActor(actor);

  renderWindow->Render();
  renderWindowInteractor->Start();

  return EXIT_SUCCESS;
}

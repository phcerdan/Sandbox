#include <vtkOctreePointLocator.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <array>

void print_locator_points(vtkAbstractPointLocator * locator)
{
    auto num_points = locator->GetDataSet()->GetNumberOfPoints();
    if(!num_points) {
        std::cout << "point locator is EMPTY" << std::endl;
        return;
    }

    for(vtkIdType index = 0; index < num_points; ++index){
        auto a_point = locator->GetDataSet()->GetPoint(index);
        std::cout << index << ": ";
        std::cout << "(" << a_point[0] << ", " << a_point[1] << ", " << a_point[2] << ")";
        std::cout << std::endl;
    }
}

void print_point_from_id(const vtkIdType id, vtkPoints * points)
{
    assert(id < points->GetNumberOfPoints());
    auto a_point = points->GetPoint(id);
    std::cout << id << ": ";
    std::cout << "(" << a_point[0] << ", " << a_point[1] << ", " << a_point[2] << ")";
    std::cout << std::endl;
}

void print_point_list(vtkIdList* idList, vtkPoints * points)
{
    auto num_ids = idList->GetNumberOfIds();
    if(!num_ids) {
        std::cout << "point list is EMPTY" << std::endl;
        return;
    }

    for (auto idIndex = 0; idIndex < num_ids; ++idIndex) {
        print_point_from_id(idList->GetId(idIndex), points);
    }
}

vtkSmartPointer<vtkOctreePointLocator>
build_octree_locator(vtkPoints * inputPoints)
{
    auto octree = vtkSmartPointer<vtkOctreePointLocator>::New();
    // Need to build a data set
    auto dataSet = vtkSmartPointer<vtkPolyData>::New();
    dataSet->SetPoints(inputPoints);
    octree->SetDataSet(dataSet);
    octree->BuildLocator();
    return octree;
}

int main(int argc, char* argv[])
{
  using PointType = std::array<double,3>;
  auto inputPoints = vtkSmartPointer<vtkPoints>::New();
  inputPoints->InsertNextPoint(0,0,0);
  inputPoints->InsertNextPoint(1,0,0);
  inputPoints->InsertNextPoint(2,0,0);

  auto octree = build_octree_locator(inputPoints);

  print_locator_points(octree);

  PointType testPoint = {{2.1, 0, 0}};
  double radius = 0.2;

  double dist2;
  auto closestId = octree->FindClosestPointWithinRadius(radius, testPoint.data(), dist2);
  vtkIdType expected_closest_id = 2;
  if(closestId == expected_closest_id) {
    std::cout << "FindClosestPointWithinRadius works as expected." << std::endl;
  }

  auto unsortedIdList = vtkSmartPointer<vtkIdList>::New();
  octree->FindPointsWithinRadius(radius, testPoint.data(), unsortedIdList);

  print_point_list(unsortedIdList, inputPoints);

  if(unsortedIdList->GetNumberOfIds() > 0){
    std::cout << "FindPointsWithinRadius is not empty. Size: " << unsortedIdList->GetNumberOfIds() << std::endl;
    if(unsortedIdList->GetId(0) == expected_closest_id){
    std::cout << "FindPointsWithinRadius works as expected." << std::endl;

    }
  } else {
    std::cout << "FAIL: FindPointsWithinRadius is empty." << std::endl;
  }
}

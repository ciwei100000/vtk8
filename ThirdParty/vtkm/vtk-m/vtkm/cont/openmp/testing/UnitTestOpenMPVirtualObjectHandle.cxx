//============================================================================
//  Copyright (c) Kitware, Inc.
//  All rights reserved.
//  See LICENSE.txt for details.
//  This software is distributed WITHOUT ANY WARRANTY; without even
//  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
//  PURPOSE.  See the above copyright notice for more information.
//
//  Copyright 2018 National Technology & Engineering Solutions of Sandia, LLC (NTESS).
//  Copyright 2018 UT-Battelle, LLC.
//  Copyright 2018 Los Alamos National Security.
//
//  Under the terms of Contract DE-NA0003525 with NTESS,
//  the U.S. Government retains certain rights in this software.
//
//  Under the terms of Contract DE-AC52-06NA25396 with Los Alamos National
//  Laboratory (LANL), the U.S. Government retains certain rights in
//  this software.
//============================================================================

#define VTKM_DEVICE_ADAPTER VTKM_DEVICE_ADAPTER_ERROR

#include <vtkm/cont/RuntimeDeviceTracker.h>
#include <vtkm/cont/openmp/DeviceAdapterOpenMP.h>
#include <vtkm/cont/testing/TestingVirtualObjectHandle.h>

namespace
{

void TestVirtualObjectHandle()
{
  using DeviceAdapterList = vtkm::ListTagBase<vtkm::cont::DeviceAdapterTagOpenMP>;
  using DeviceAdapterList2 =
    vtkm::ListTagBase<vtkm::cont::DeviceAdapterTagSerial, vtkm::cont::DeviceAdapterTagOpenMP>;

  auto tracker = vtkm::cont::GetGlobalRuntimeDeviceTracker();

  tracker.ForceDevice(vtkm::cont::DeviceAdapterTagOpenMP{});
  vtkm::cont::testing::TestingVirtualObjectHandle<DeviceAdapterList>::Run();

  tracker.Reset();
  vtkm::cont::testing::TestingVirtualObjectHandle<DeviceAdapterList2>::Run();
}

} // anonymous namespace

int UnitTestOpenMPVirtualObjectHandle(int, char* [])
{
  return vtkm::cont::testing::Testing::Run(TestVirtualObjectHandle);
}

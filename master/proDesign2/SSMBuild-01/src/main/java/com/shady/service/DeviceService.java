package com.shady.service;

import com.shady.pojo.Devices;

import java.util.List;

public interface DeviceService {
    public Devices queryDeviceById(int device_id);
    public List<Devices> queryAllDevice();
}

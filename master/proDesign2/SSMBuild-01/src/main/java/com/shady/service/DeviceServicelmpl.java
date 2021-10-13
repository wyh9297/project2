package com.shady.service;

import com.shady.dao.DeviceMapper;
import com.shady.pojo.Devices;
import org.springframework.beans.factory.annotation.Autowired;

import java.util.List;

public class DeviceServicelmpl implements DeviceService{
    @Autowired
    private DeviceMapper deviceMapper;
    public void setDeviceMapper(DeviceMapper deviceMapper) {
        this.deviceMapper = deviceMapper;
    }

    public Devices queryDeviceById(int device_id) {
        return deviceMapper.queryDeviceById(device_id);
    }
    public List<Devices> queryAllDevice(){
        return deviceMapper.queryAllDevice();
    }


}

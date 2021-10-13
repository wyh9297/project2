package com.shady.dao;

import com.shady.pojo.Devices;
import org.apache.ibatis.annotations.Param;

import java.util.List;

public interface DeviceMapper {
    public Devices queryDeviceById(@Param("device_id") int device_id);
    public List<Devices> queryAllDevice();
}

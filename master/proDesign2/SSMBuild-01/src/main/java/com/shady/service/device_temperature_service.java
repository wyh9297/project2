package com.shady.service;

import com.shady.pojo.device_temperature;

import java.util.List;

public interface device_temperature_service {
    List<device_temperature> queryDeviceTemperature(int device_id);//按设备号查询记录
}

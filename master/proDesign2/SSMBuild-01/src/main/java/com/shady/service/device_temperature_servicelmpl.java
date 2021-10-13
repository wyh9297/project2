package com.shady.service;

import com.shady.dao.device_temperatureMapper;
import com.shady.pojo.device_temperature;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;
@Service
public class device_temperature_servicelmpl implements device_temperature_service{
    @Autowired
    private device_temperatureMapper device_temperatureMapper;
    public List<device_temperature> queryDeviceTemperature(int device_id) {
        return device_temperatureMapper.queryDeviceTemperature(device_id);
    }
}

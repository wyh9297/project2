package com.shady.dao;

import com.shady.pojo.device_temperature;
import org.apache.ibatis.annotations.Param;

import java.util.List;

public interface device_temperatureMapper {
    List<device_temperature> queryDeviceTemperature(@Param("device_id")int device_id);
}

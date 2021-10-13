package com.shady.controller;



import com.shady.pojo.Devices;
import com.shady.pojo.device_temperature;
import com.shady.service.DeviceService;
import com.shady.service.DeviceServicelmpl;
import com.shady.service.device_temperature_service;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.stereotype.Service;

import javax.servlet.http.HttpSession;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
@Controller
public class DeviceController{
    @Autowired
    private DeviceService deviceService;
    @Autowired
    private device_temperature_service device_temperature_service;
    @RequestMapping("/allDevice")
    public String allDevices(Model model){
        List<Devices> devices = new ArrayList<Devices>();
        devices = deviceService.queryAllDevice();
        List<Float> temperatures=new ArrayList<Float>();
        List<String> warning=new ArrayList<String>();
        for (Devices temp:devices){
            temperatures.add(device_temperature_service.queryDeviceTemperature(temp.getDevice_id()).get(0).getTemperature());
        }
        for (Float i : temperatures){
            if(i>50){
                warning.add("温度过高");
            }
            else{
                warning.add("正常");
            }
        }
        model.addAttribute("warning",warning);
        model.addAttribute("devices",devices);
        model.addAttribute("temperatures",temperatures);
        return "allDevice";
    }
    @RequestMapping("/deviceDetail")
    public String deviceDetail(int id, Model model){
        Devices device = deviceService.queryDeviceById(id);//查询当前设备信息
        List<device_temperature> device_temperatures = new ArrayList<device_temperature>();
        device_temperatures = device_temperature_service.queryDeviceTemperature(id);
        for(device_temperature temp: device_temperatures ){
            SimpleDateFormat simpleDateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
            String res=temp.getTime();//获取时间戳
            System.out.println("时间戳："+res);
            long lt=Long.valueOf(res).longValue();

            Date date=new Date(lt);
            String time=simpleDateFormat.format(date);
            System.out.println("时间："+time);
//            borrowtimes.add(borrowtime);
            temp.setTime(time);
        }
        model.addAttribute("device",device);

        model.addAttribute("device_temperatures",device_temperatures);
        return "deviceDetail";
    }
}
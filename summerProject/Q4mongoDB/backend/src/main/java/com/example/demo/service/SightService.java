package com.example.demo.service;

import com.example.demo.repository.SightRepository;
import com.example.demo.model.Sight;
import org.springframework.data.domain.Example;
import org.springframework.stereotype.Service;

import java.io.IOException;
import java.util.List;
//
@Service
public class SightService {

    private SightRepository sightRepository;

    public SightService(SightRepository sightRepository) {
        this.sightRepository = sightRepository;
    }

    public List<Sight> getSightByZone(String zone) throws NullPointerException, IOException {
        if (zone == null || zone.trim().isEmpty()) {
            throw new IllegalArgumentException("Zone name must not be empty");
        }
        Sight temp = new Sight();// 建立範例物件
        temp.setZone(zone.trim());//trim() can remove space from end and start
        //of:Create a new Example using the given ExampleMatcher.
        Example<Sight> example = Example.of(temp); // 建立符合要查勳的zone的範例
        System.out.println("Find Sights from mongoDB...");
        List<Sight> resultList = sightRepository.findAll(example);
        if(resultList != null){
            for (Sight s : resultList) {
                System.out.println(s.toString());
            }
        }
        else {
            System.out.println("Not result for " + zone +"區");
        }
        return resultList;
    }
}

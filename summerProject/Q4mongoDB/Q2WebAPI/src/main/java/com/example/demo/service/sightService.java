package com.example.demo.service;

import com.example.demo.repository.SightRepository;
import com.org.model.Sight;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Example;
import org.springframework.stereotype.Service;

import java.io.IOException;
import java.util.List;
import java.util.Optional;

@Service
public class sightService {

    @Autowired
    private final SightRepository sightRepository;

    public sightService(SightRepository sightRepository) {
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
                System.out.println(s.getZone());
            }
        }
        else {
            System.out.println("Not result for " + zone +"區");
        }
        return resultList;
    }
}

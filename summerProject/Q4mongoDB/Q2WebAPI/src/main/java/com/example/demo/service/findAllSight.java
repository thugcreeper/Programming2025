package com.example.demo.service;

import com.example.demo.repository.SightRepository;
import com.org.model.Sight;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class findAllSight{
    private final SightRepository sightRepository;
    @Autowired
    public findAllSight(SightRepository sightRepository) {
        this.sightRepository = sightRepository;
    }
    public void showAllSights() {
        List<Sight> sightList = sightRepository.findAll();
        sightList.forEach(item -> System.out.println(item.toString()));
    }
}

package com.example.demo.service;

import com.example.demo.repository.SightRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class deleteSights {
    private final SightRepository sightRepository;
    @Autowired
    public deleteSights(SightRepository sightRepository) {
        this.sightRepository = sightRepository;
    }

    public void deleteByName(String zone){
        sightRepository.deleteById(zone);
        System.out.println("Deleting Sight with id " + zone + "...");
    }
    public void deleteAllSights(){
        sightRepository.deleteAll();
        System.out.println("All sights Deleted!!!");
    }
}

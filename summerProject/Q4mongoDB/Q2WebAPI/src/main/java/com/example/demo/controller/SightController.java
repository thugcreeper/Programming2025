package com.example.demo.controller;

import com.example.demo.repository.SightRepository;
import com.example.demo.service.sightService;
import com.org.model.Sight;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import com.org.crawler.KeelungSightsCrawler;

import java.io.IOException;
import java.util.*;
//run and enter http://127.0.0.1:8080/SightAPI?zone=七堵
//Web API
@RestController
public class SightController{
    private final SightRepository sightRepository;

    public SightController(SightRepository sightRepository){
        this.sightRepository = sightRepository;
    }
    @GetMapping("/SightAPI")
    @CrossOrigin("http://localhost:5173/")//設定允許CORS的網站
    //@RequestParam is used to extract data from the query parameters of a request URL
    //?zone="七堵" 會擷取七堵
    public ResponseEntity<Sight[]> getItems(@RequestParam String zone) {
        sightService newCrawler =new sightService(sightRepository);
        Sight errorSight = new Sight();
        try{
            Sight[] crawlSights= newCrawler.getSightByZone(zone).toArray(new Sight[0]);
            return  crawlSights != null ? ResponseEntity.ok(crawlSights):
                                          ResponseEntity.notFound().build();//build建立一個沒有內容的ResponseEntity
        }
        catch (IOException e) {
            errorSight.setSightName("Error: Please check your network connection or the website URL. Reason: %s".formatted(e.getMessage()));
            return ResponseEntity.internalServerError().body(new Sight[] { errorSight });
        }
        catch (NullPointerException e) {
            errorSight.setSightName("No results. Please enter a valid Keelung City zone.");
            return ResponseEntity.badRequest().body(new Sight[] { errorSight });
        }
    }
}

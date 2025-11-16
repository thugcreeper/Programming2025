package com.example.demo.controller;

import com.example.demo.repository.SightRepository;
import com.example.demo.service.SightService;
import com.example.demo.model.Sight;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.io.IOException;
import java.util.*;
//run and enter http://127.0.0.1:8080/SightAPI?zone=七堵
//Web API
@RestController
@CrossOrigin("http://localhost:5173/")//設定允許CORS的網站
public class SightController{
    private final String[] districts= {"七堵","中山","中正","仁愛","安樂","信義","暖暖"};
    private final SightRepository sightRepository;

    public SightController(SightRepository sightRepository){
        this.sightRepository = sightRepository;
    }
    //http://127.0.0.1:8080/SightAPI/預設輸出所有景點
    @GetMapping("/SightAPI/")
    public ResponseEntity<Sight[]> getAllSights(){
        Sight errorSight = new Sight();
        SightService newCrawler =new SightService(sightRepository);
        try{
            List<Sight> allSights = new ArrayList<>();
            for (String district : districts) {
                List<Sight> sights = newCrawler.getSightByZone(district);
                allSights.addAll(sights);
            }
            if (allSights.isEmpty()) {
                errorSight.setSightName("Can't find any sight in database");
                return ResponseEntity.ok(new Sight[]{errorSight});
            }
            //toArray轉成Sight[]
            return ResponseEntity.ok(allSights.toArray(new Sight[0]));
        }
        catch (IOException e) {
            errorSight.setSightName("Error: Please check your network connection or the website URL. Reason: %s".formatted(e.getMessage()));
            return ResponseEntity.internalServerError().body(new Sight[] { errorSight });
        }
    }

    @GetMapping("/SightAPI")
    //@RequestParam is used to extract data from the query parameters of a request URL
    //?zone="七堵" 會擷取七堵
    public ResponseEntity<Sight[]> getItems(@RequestParam(required = false) String zone) {
        SightService newCrawler =new SightService(sightRepository);
        Sight errorSight = new Sight();
        try{
            Sight[] crawlSights= newCrawler.getSightByZone(zone).toArray(new Sight[0]);
            if(crawlSights.length>0){
                return ResponseEntity.ok(crawlSights);
            }
            else{
                errorSight.setSightName("Zone not found: " + zone);
                return ResponseEntity.badRequest().body(new Sight[] { errorSight });
            }
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

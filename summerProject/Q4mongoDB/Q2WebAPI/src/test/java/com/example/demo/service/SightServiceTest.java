package com.example.demo.service;

import com.org.model.Sight;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

import java.io.IOException;
import java.util.List;
//測試從mongoDB抓資料
@SpringBootTest
public class SightServiceTest {

    @Autowired
    private sightService sightService;

    @Test
    public void testGetSightsByZone() {
        try{
            List<Sight> result = sightService.getSightByZone("七堵");
            System.out.println(result.toString());
            for (Sight s : result) {
                System.out.println(s.toString());
            }
        }
        catch (IOException e){
            System.err.println("Error: Please check your network connection or the website URL. Reason: %s".formatted(e.getMessage()));
        }
    }
}

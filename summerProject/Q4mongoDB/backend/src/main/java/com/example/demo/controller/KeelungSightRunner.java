package com.example.demo.controller;

import com.example.demo.service.deleteSights;
import com.example.demo.service.findAllSight;
import com.example.demo.model.Sight;
import com.example.demo.repository.SightRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.ApplicationArguments;
import org.springframework.boot.ApplicationRunner;
import org.springframework.stereotype.Component;
import com.org.crawler.KeelungSightsCrawler;

import java.util.ArrayList;
import java.util.Arrays;

//ApplicationRunner，當啟動DemoApplication.java時，自動呼叫爬蟲程式
@Component
public class KeelungSightRunner implements ApplicationRunner {
    private final String[] districts= {"七堵","中山","中正","仁愛","安樂","信義","暖暖"};
    @Autowired
    private SightRepository KeelungSightRepo;

    ArrayList<Sight[]> sights = new ArrayList<Sight[]>();

    @Override
    public void run(ApplicationArguments args) throws Exception {
        System.out.println("Call KeelungSight crawler");
        KeelungSightsCrawler crawler = new KeelungSightsCrawler();
        findAllSight finder = new findAllSight(KeelungSightRepo);
        deleteSights deleter = new deleteSights(KeelungSightRepo);
        int totalLength=0;

        for(int i=0;i<districts.length;i++){//測試完記得改成districts.length
            try{
                Sight[] sights = crawler.getItems(districts[i]);
                //saveAll要接iterable的entity作為參數，因此要Array.asList
                KeelungSightRepo.saveAll(Arrays.asList(sights));
                //sights.add(crawler.getItems(districts[i]));
                System.out.println(districts[i]+"區 Saved successfully :)");
            }
            catch (Exception e) {
                System.err.println("Error! reason:"+e.getMessage());
            }
        }
        for (Sight[] districtSights : sights) {
            for(Sight s : districtSights){
                System.out.println(s);
            }
        }

        /*Testing
        System.out.println("Fetching all sights from database...");
        finder.showAllSights();
        String deleteZone = "仙洞巖";
        deleter.deleteByName(deleteZone);
        */

    }
}

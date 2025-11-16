package com.org.crawler;
import com.example.demo.model.Sight;
import java.io.IOException;

public class KeelungSightsCrawlerTest {
    public static void main(String[] args) {
        KeelungSightsCrawler crawler = new KeelungSightsCrawler();
        try{
            Sight[] sights = crawler.getItems("七堵");
            for (Sight s : sights){
                System.out.println(s);
            }
        }
        catch (IOException e){
            System.err.println("Error: Please check your network connection or the website URL. Reason: %s".formatted(e.getMessage()));

        }
        catch (NullPointerException e){
            System.err.println("No results,please enter a district which exists in Keelung City");
        }
    }
}

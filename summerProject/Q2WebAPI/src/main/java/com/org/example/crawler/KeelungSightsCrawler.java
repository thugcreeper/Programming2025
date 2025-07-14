package com.org.example.crawler;
import java.util.*;
import com.org.example.model.Sight;
import org.jsoup.Jsoup;
import java.lang.NullPointerException;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;
import java.io.IOException;

public class KeelungSightsCrawler{
    public Sight[] getItems(String target) throws NullPointerException,IOException{
        String mainURL = "https://www.travelking.com.tw/tourguide/taiwan/keelungcity/";
        Sight[] siteArray = null;
        boolean found = false;
        try {
            int index=0;
            Document doc = Jsoup.connect(mainURL).get();
            Elements zones = doc.select("div.box h4");
            for (Element zone : zones) {
                if (zone.text().contains(target)) {
                    found = true;
                    // Get the next <ul> list under the same structure as h4
                    Element ul = zone.nextElementSibling();//h4 和 ul是兄弟關係
                    if (ul != null) {
                        Elements sights = ul.select("li a");
                        siteArray = new Sight[sights.size()];//必須先設定大小
                        for (Element sight : sights) {
                            Sight mysight = new Sight();
                            String link = "https://www.travelking.com.tw" + sight.attr("href");
                            Document sitePage = Jsoup.connect(link).get();//connect to sight website
                            mysight.setSightName(sight.text());
                            mysight.setZone(target);
                            //select the elements with temprop="address" and select its content attribute
                            mysight.setAddress(sitePage.select("meta[itemprop=address]").attr("content"));
                            mysight.setCategory(sitePage.select("span[property='rdfs:label']").text());
                            mysight.setDescription(sitePage.select("meta[itemprop=description]").attr("content"));
                            mysight.setPhotoURL(sitePage.select("meta[itemprop=image]").attr("content"));
                            //System.out.println(mysight.toString());
                            siteArray[index++]=mysight;
                        }
                    }

                }
            }
            if (!found) {
                throw new NullPointerException();//沒有搜尋結果的例外
            }
        } catch (IOException e) {
            throw new IOException();
        }
        return siteArray;
    }
}

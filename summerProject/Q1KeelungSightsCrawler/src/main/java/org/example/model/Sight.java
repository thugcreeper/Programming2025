package org.example.model;

public class Sight {
    private String sightName;
    private String zone;
    private String category;
    private String photoURL;
    private String address;
    private String description;
/*
    public Sight(String sightName, String zone, String category,//Constructor
                 String photoURL, String address, String description) {
        this.sightName = sightName;
        this.zone = zone;
        this.category = category;
        this.photoURL = photoURL;
        this.address = address;
        this.description = description;
    }*/

    public void setSightName(String sightName){
        this.sightName=sightName;
    }

    public String getSightName(){
        return sightName;
    }

    public void setZone(String zone){
        this.zone=zone;
    }
    public String getZone(){
        return zone;
    }

    public void setCategory(String category){
        this.category=category;
    }
    public String getCategory(){
        return category;
    }

    public void setPhotoURL(String photoURL){
        this.photoURL=photoURL;
    }
    public String getPhotoURL(){
        return photoURL;
    }

    public void setAddress(String address){
        this.address=address;
    }
    public String getAddress(){
        return address;
    }
    public void setDescription(String description){
        this.description=description;
    }
    public String getDescription(){
        return description;
    }
    private String newline(String text, int lineLength) {//換行功能
        StringBuilder sb = new StringBuilder();
        int i = 0;
        while (i < text.length()) {
            int end = Math.min(i + lineLength, text.length());
            sb.append(text, i, end).append("\n");
            i = end;
        }
        return sb.toString();
    }

    @Override
    public String toString() {
        return
                "SightName: "  + sightName + "\n" +
                "Zone: " + zone + "區\n"  +
                "Category: " + category + "\n" +
                "PhotoURL: "  + photoURL + "\n" +
                "Description: "  + newline(description,30) +"\n"+
                "Address: " + address + "\n";

    }
}



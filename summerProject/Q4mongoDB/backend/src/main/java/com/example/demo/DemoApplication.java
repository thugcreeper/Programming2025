package com.example.demo;

import io.github.cdimascio.dotenv.Dotenv;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
//run and enter http://127.0.0.1:8080/SightAPI?zone=七堵
@SpringBootApplication
public class DemoApplication {

	public static void main(String[] args) {
		Dotenv dotenv = Dotenv.configure().ignoreIfMissing().load();
		dotenv.entries().forEach(entry -> {
			System.setProperty(entry.getKey(), entry.getValue());
		});
		System.out.println("MONGODB_URI: " + System.getProperty("MONGODB_URI"));
		SpringApplication.run(DemoApplication.class, args);

	}

}

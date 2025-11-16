package com.example.demo.repository;
import com.example.demo.model.Sight;
import org.springframework.data.mongodb.repository.MongoRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface SightRepository extends MongoRepository<Sight, String> {

}

function fetchSightData(district) {
  return fetch(`http://127.0.0.1:8080/SightAPI?zone=${district}`, { method: "GET" })
    .then(response => {
      if (!response.ok) throw new Error('Network response was not ok');
      return response.json();
    })
    .catch(error => {
      window.alert('Error fetching data: ' + error.message);
    });
}
export default fetchSightData;

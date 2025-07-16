import { useState } from 'react'
import fetchSightData from './fetchSightJson.jsx'
import reactLogo from './assets/react.svg'
import viteLogo from '/vite.svg'
import './App.css'
//cd C:\Users\User\Desktop\Q3RWDPractice
//npm run dev
//enter http://localhost:5173/
function App() {
  const [data, setData] = useState([])

  const handleFetch = async (district) => {
    const result = await fetchSightData(district);
    if (result) {
      setData(result);
      console.log('Data fetched successfully:', result);
      let sightName =JSON.parse(JSON.stringify(result)).map(item => item.sightName);
      let sightZone = JSON.parse(JSON.stringify(result)).map(item => item.zone);
      let sightcategory = JSON.parse(JSON.stringify(result)).map(item => item.category);
      let sightImage = JSON.parse(JSON.stringify(result)).map(item => item.photoURL);
      let sightAddress = JSON.parse(JSON.stringify(result)).map(item => item.address);
      let sightDescription = JSON.parse(JSON.stringify(result)).map(item => item.description);
    }
    else{
      console.error('Failed to fetch data');
    }
  }

  return (
    <div className="min-h-screen bg-gradient-to-b from-blue-100 to-blue-300 flex flex-col items-center justify-center bg-blue-100">
      <h1 className="text-6xl text-red-500 my-5 mb-20 font-serif">基隆市景點瀏覽器</h1>
      <div className="flex flex-wrap gap-x-4 gap-y-2 justify-center">
        <button onClick={() => handleFetch('中山區')}>中山區</button>
          <button onClick={() => handleFetch('信義區')}>信義區</button>
          <button onClick={() => handleFetch('仁愛區')}>仁愛區</button>
          <button onClick={() => handleFetch('中正區')}>中正區</button>
          <button onClick={() => handleFetch('安樂區')}>安樂區</button>
          <button onClick={() => handleFetch('七堵區')}>七堵區</button>
          <button onClick={() => handleFetch('暖暖區')}>暖暖區</button>
      </div>
      {/* Display fetched sights here */}
      <div id='showSights' className="flex flex-wrap gap-4 justify-center mt-10">
        {data.map((item, index) => (
          <div key={index} className="card bg-white shadow-xl rounded-xl w-4/5 max-w-2xl overflow-hidden hover:shadow-2xl transition-shadow duration-300">      
            <div className="p-4">
              <h2 className="text-xl font-semibold text-blue-800">名稱:{item.sightName}</h2>
              <p className="font-semibold text-indigo-700 ">區域: {item.zone}</p>
              <p className="font-semibold text-teal-700">分類: {item.category}</p>
              <p className="font-semibold text-pink-700">
                {/*lambda function:let func=(arg1,arg2...)=>{expression} */}
                <button id='addrButton' onClick={() => window.open(`${item.mapURL}`, '_blank')}>地址
              </button>&nbsp;{item.address}</p>
              <button id={`moreInfobtn-${index}`} 
                      onClick={() => document.getElementById(`moreInfo-${index}`).classList.toggle('collapse')}
                      className='moreInfobtn'>詳細資訊</button>  
              <div className='collapse' id={`moreInfo-${index}`}>
                <img src={item.photoURL} alt={item.sightName} className="w-full h-auto object-cover rounded-xl border-blue-400 border-solid border-5" />
                <p className="font-semibold text-black mt-2">介紹:{item.description}</p>
              </div>

            </div>
          </div>
        ))}
      </div>
    </div>
  )
}

export default App

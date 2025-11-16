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
    <div className="w-full min-h-screen bg-gradient-to-b from-blue-100 to-blue-300 px-4 py-6">
      {/*max-md表示width < 48rem(768px)*/}
      <a href='https://www.travelking.com.tw/tourguide/taiwan/keelungcity/' target='_blank' rel='noopener noreferrer'>
        <h1 className="max-sm:text-3xl sm:text-4xl md:text-5xl lg:text-6xl text-red-500 my-5 mb-20 font-serif ">基隆市景點瀏覽器</h1>
      </a>
      <div className="flex flex-wrap gap-x-4 gap-y-2 justify-center">
        <button onClick={() => handleFetch('中山')} >中山區</button>
          <button onClick={() => handleFetch('信義')} >信義區</button>
          <button onClick={() => handleFetch('仁愛')} >仁愛區</button>
          <button onClick={() => handleFetch('中正')} >中正區</button>
          <button onClick={() => handleFetch('安樂')} >安樂區</button>
          <button onClick={() => handleFetch('七堵')} >七堵區</button>
          <button onClick={() => handleFetch('暖暖')} >暖暖區</button>
      </div>
      <div id="searchingHint" className='hidden text-center text-2xl font-bold text-blue-800 mt-10'>
        搜尋中...
      </div>
      {/* Display fetched sights here */}
      <div id='showSights'>
        {data.map((item, index) => (
          <div
            key={index}
            className={`card w-full bg-white shadow-xl rounded-xl overflow-hidden hover:shadow-2xl transition-shadow duration-300
              ${data.length === 1 ? 'col-span-1 sm:col-span-2 md:col-span-3' : ''}`}
          >{/* Card content */}
            <div className="p-4">{/*padding*/}
              {/*max-sm:小於40rem(640px)時font size=xl*/}
              <h2 className="max-sm:text-xl sm:text-2xl md:text-3xl font-semibold text-blue-800">{item.sightName}</h2>
              <p className="max-sm:text-lg sm:text-xl md:text-2xl font-semibold text-indigo-700">區域: {item.zone}</p>
              <p className="max-sm:text-lg sm:text-xl md:text-2xl font-semibold text-teal-700">分類: {item.category}</p>
              <p className="max-sm:text-lg sm:text-xl md:text-2xl font-semibold text-pink-700">
                <button id="addrButton" onClick={() => window.open(`${item.mapURL}`, '_blank')}>地址</button>
                <p>{item.address}</p>
              </p>
              <button
                id={`moreInfobtn-${index}`}
                /* ` is used for template string and you can interpolate variables or expression*/ 
                onClick={() => document.getElementById(`moreInfo-${index}`).classList.toggle('collapse')}
                className="moreInfobtn max-sm:text-sm sm:text-base md:text-lg"
              >
                詳細資訊
              </button>
              <div className="collapse" id={`moreInfo-${index}`}>
                <img
                  src={item.photoURL}
                  alt={item.sightName}
                  className="w-full h-auto object-cover rounded-xl border-blue-400 border-solid border-5"
                />
                <p className="max-sm:text-sm sm:text-base md:text-lg font-semibold text-black mt-2">介紹: {item.description}</p>
              </div>
            </div>
          </div>
        ))}
      </div>
    </div>
  )
}

export default App

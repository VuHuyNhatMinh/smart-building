import { useState, useEffect} from 'react';
//This is useFetch for AC:0B:FB:CE:AD:1F
export const useFetch = (url) => {

  console.log("useFetch start!!")

  const [sensorsHumidity, setSensorsHumidity] = useState([])
  const [sensorsTemperature, setSensorsTemperature] = useState([])

  const getSensors = async () => {
    const response = await fetch(url,{
      'method':'GET',
      headers: {
        'Content-Type':'application/json',
      }
    });
    const new_sensors = await response.json()
    if(new_sensors)
    {
      console.count("SUCCESS");
      // console.count(new_sensors);
          let new_sensors_humidity = new_sensors.map((new_sensor)=>{return new_sensor.hum})
          let new_sensors_temperature = new_sensors.map((new_sensor)=>{return new_sensor.temp})
          setSensorsTemperature(new_sensors_temperature);
          setSensorsHumidity(new_sensors_humidity);
    }
    else
    {
      console.count("NO DATA !!!!!")
    }
    
  };

  useEffect(() => {   
    setTimeout(() => {getSensors()}, 1000); 
    // Mỗi khi fetch dữ liệu về thì sẽ trigger hàm setSensors rồi sẽ re-render lại component rồi sẽ lại 
    // trigger useEffect và rồi lại trigger getSensors lần nữa
  });

  return {sensorsHumidity, sensorsTemperature};
};

export default useFetch;
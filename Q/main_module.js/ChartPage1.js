import React, { useState, useEffect } from "react";
import {SpiderManS_data} from './module/SpiderManS_data.js';

import {useFetch} from './module/useFetch';

import LineChartHum1 from './module/LineChartHum1'
import LineChartTem1 from './module/LineChartTem1'



let ChartPage1 = () =>    //tên component phải là Capital    //truyền các component con vào component lớn này 
{
  let url = "http://127.0.0.1:8000/api/v1/sensors/listCreate1/";
  //Mỗi lần fetch lại data mới thì cái sensros sẽ bị thay đổi state nên là sẽ re-render lại cái SensorsList chứa cái state này nhưng cái 
  //SpidermanList sẽ ko re-render lại vì prop của nó vẫn thế 

  const {sensorsHumidity, sensorsTemperature} = useFetch(url);    //cái này là object destructor
  
  

  return (
    <div>
      {/* <SensorList sensors={sensorsHumidity} /> */}

      {/* <SpiderManList SpiderManS_data={SpiderManS_data}/> */}

      <LineChartHum1 data={sensorsHumidity} />
      <LineChartTem1 data={sensorsTemperature} />
    </div>
  );
};

const SensorList= React.memo(({sensors}) => {
  // console.count("SensorsList");
  return (
      <ul>
        {sensors.map((sensor) => {
        return (
          <li key={sensor.id}>
            <h1>{sensor.mac}</h1>
            <h2>{sensor.temp}</h2>
            <h2>{sensor.hum}</h2>
          </li>
        );
      })}
      </ul>
  );
});




const SpiderManList = React.memo(({SpiderManS_data}) => {
  // console.count('SpiderManlist');
  return (<>
    {
      SpiderManS_data.map(
      (spider)=>{ 
        return <SpiderMan key={spider.id}  {...spider} />;  
      }
      )
    }
  </>);
});

let SpiderMan = ({image, name, year,}) =>         
{  

  const clickHandler = (name) => {console.log(name)}; 
  const funcWithPara = (name) => {console.log(name)};  

  return (

      <article className="spiderman_small_component" onMouseOver={ () => console.log(name)}>
        <img src={image}/>
        <h1 onClick={ clickHandler }>{name}</h1>  
        <h2 onClick={ ()=>{alert(year)} }>{year}</h2>
        <button type="button" onClick={ () => {funcWithPara(name)} }>funcWithPara</button>
        <br />
        <br />
      </article>
  )
};

export default ChartPage1;
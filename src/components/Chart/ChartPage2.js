import React from "react";

import {useFetch} from './module/useFetch';

import LineChartHum2 from './module/LineChartHum2'
import LineChartTem2 from './module/LineChartTem2'



let ChartPage2 = () =>    //tên component phải là Capital    //truyền các component con vào component lớn này 
{
  let url = "http://127.0.0.1:8000/api/v1/sensors/listCreate2/";
  //Mỗi lần fetch lại data mới thì cái sensros sẽ bị thay đổi state nên là sẽ re-render lại cái SensorsList chứa cái state này nhưng cái 
  //SpidermanList sẽ ko re-render lại vì prop của nó vẫn thế 

  const {sensorsHumidity, sensorsTemperature} = useFetch(url);    //cái này là object destructor

  return (
    <div>
      <LineChartHum2 data={sensorsHumidity} />
      <LineChartTem2 data={sensorsTemperature} />
    </div>
  );
};

export default ChartPage2;
import React from "react";
import {useFetch} from './module/useFetch';
import LineChartHum1 from './module/LineChartHum1'
import LineChartTem1 from './module/LineChartTem1'



let ChartPage1 = ({id}) =>    //tên component phải là Capital    //truyền các component con vào component lớn này 
{
  let url = `http://localhost:8000/api/v1/sensors/listCreate/${id}`;
  //Mỗi lần fetch lại data mới thì cái sensros sẽ bị thay đổi state nên là sẽ re-render lại cái SensorsList chứa cái state này nhưng cái 
  //SpidermanList sẽ ko re-render lại vì prop của nó vẫn thế 

  const {sensorsHumidity, sensorsTemperature} = useFetch(url);    //cái này là object destructor

  return (
    <div>
      <LineChartHum1 data={sensorsHumidity} id={id}/>
      <LineChartTem1 data={sensorsTemperature} id={id}/>
    </div>
  );
};

export default ChartPage1;
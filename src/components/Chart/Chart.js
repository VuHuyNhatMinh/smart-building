import React from 'react';

import ChartPage1 from './ChartPage1';
import ChartPage2 from './ChartPage2';

const Chart = ({id}) => {
  console.log(id)
  return (<>
    {id===1? <ChartPage1/>: null}
    {id===2? <ChartPage2/>: null}
  </>
  );
};
export default Chart;
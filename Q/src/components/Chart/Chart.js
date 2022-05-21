import React from 'react';

import ChartPage1 from './ChartPage1';
import ChartPage2 from './ChartPage2';

const Chart = ({id}) => {
  console.log(id)
  return (<>
    {<ChartPage1 id={id}/>}
  </>
  );
};
export default Chart;
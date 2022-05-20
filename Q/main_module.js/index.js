import React from 'react';
// react router
import { BrowserRouter as Router, Route, Routes, Link, NavLink, BrowserRouter } from "react-router-dom"
import ChartPage1 from './ChartPage1';
import ChartPage2 from './ChartPage2';
import Home from './Home';
import Navbar from './Navbar';
// export default ReactRouter;

const ReactRouter = () => {
  return (<>
  <ChartPage1/>
  <ChartPage2/>
  </>
      // <BrowserRouter>
      // <Navbar/>
         
      //    <Routes>
      //       <Route exact path='/' element={<Home/>}></Route>
      //       <Route exact path='/ChartPage1'  element={<ChartPage1/>}></Route>
      //       <Route exact path='/ChartPage2'  element={<ChartPage2/>}></Route>
      //    </Routes>
      // </BrowserRouter>
  );
};
export default ReactRouter;
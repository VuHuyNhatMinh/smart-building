import React from 'react';
import ReactDOM from 'react-dom/client';   //cái ReactDom để insert cái component vào html
import './index.css';
import App from './App';

// ReactDom.render(<Greeting/>, document.getElementById('root'));
const root = ReactDOM.createRoot(document.getElementById("root"));    //không hỗ trợ ReactDom nữa mà dùng cái này
root.render(
  // <React.StrictMode>     //do cái này nên bị hai lần
  //   <App/>
  // </React.StrictMode>
  <React.Fragment>
    <App/>
  </React.Fragment>
);


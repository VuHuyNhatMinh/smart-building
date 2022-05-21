import React from "react";
import './style.css'

function Area({funcSetBtn}) {
    return (
        <>
            <div className="area--bg"></div>
            <button className="area--btn" onClick={() => {funcSetBtn(1)}}>1</button>
            <button className="area--btn" onClick={() => {funcSetBtn(2)}}>2</button>

        </>
    )
}

export default Area;
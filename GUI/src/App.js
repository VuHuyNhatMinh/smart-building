import React from "react";
import 'bootstrap/dist/css/bootstrap.min.css';

import Header from "./components/Header/Navbar";
import Area from "./components/Area/Area";
import Chart from "./components/Chart/Chart";
import { Grid } from "@material-ui/core";
import { useState } from "react";

function App() {
    const [btn, setBtn] = useState(0);
    let funcSetBtn = (id) => {
        setBtn(id);
    };
    return (
        <>
            <Header />
            <Grid container spacing={3} style={{width:'100%'}}>
                <Grid item xs={12} md={6}>
                    <Area funcSetBtn = {funcSetBtn}/>
                </Grid>
                <Grid item xs={12} md={6}>
                    <Chart id = {btn}/>
                </Grid>
            </Grid>
        </>
    )
}

export default App;
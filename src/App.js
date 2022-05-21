import React from "react";

import Header from "./components/Header/Header";
import Area from "./components/Area/Area";
import Chart from "./components/Chart/Chart";
import { Grid } from "@material-ui/core";

function App() {
    return (
        <>
            <Header />
            <Grid container spacing={3} style={{width:'100%'}}>
                <Grid item xs={12} md={6}>
                    <Area />
                </Grid>
                <Grid item xs={12} md={6}>
                    <Chart />
                </Grid>
            </Grid>
        </>
    )
}

export default App;
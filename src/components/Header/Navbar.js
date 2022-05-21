import React from 'react'
import {NavDropdown, Nav, Navbar, Container} from 'react-bootstrap'
import {
  BrowserRouter,
  Routes,
  Route,
  Link
} from "react-router-dom";

import { About } from './About';
import { Contact } from './Contact';
import Home from './Home';

export default function Header() {
  return (
    <BrowserRouter>
    <div className="App">
        <Navbar bg="dark" variant='dark' expand="sm">
          <Container>
            <Navbar.Brand as={Link} to="/Home">Smart Building</Navbar.Brand>
            <Navbar.Toggle aria-controls="basic-navbar-nav" />
            <Navbar.Collapse id="basic-navbar-nav">
              <Nav className="me-auto">
                <Nav.Link as={Link} to="/About">About</Nav.Link>
                <Nav.Link as={Link} to="/Contact">Contact</Nav.Link>
                <NavDropdown title="Sensor" id="basic-nav-dropdown">
                  <NavDropdown.Item href="/Sensor/1">Sensor 1</NavDropdown.Item>
                  <NavDropdown.Item href="/Sensor/2">Sensor 2</NavDropdown.Item>
                  <NavDropdown.Item href="/Sensor/3">Sensor 3</NavDropdown.Item>


                  
                  
                  <NavDropdown.Divider />
                  <NavDropdown.Item href="#action/3.4">Separated link</NavDropdown.Item>
                </NavDropdown>
              </Nav>
            </Navbar.Collapse>
          </Container>
        </Navbar>

        <div>
          <Routes>
            <Route path="/Home" element={<Home/>}/>
            <Route path="/About" element={<About/>}/>
            <Route path="/Contact" element={<Contact/>}/>
          </Routes>

        </div>
    </div>
    </BrowserRouter>
  )
}

import React, {useState, useEffect} from 'react';
import { First } from 'react-bootstrap/esm/PageItem';

function App() {
  const [joke, setJoke]=useState("loading");
  const[fname, setfname]=useState("abhishek");
  const[sname, setsname]=useState("sahu");
  const newJoke=(first, second)=>{
    fetch(`http://api.icndb.com/jokes/random?firstName=${first}&lastName=${second}`)
    .then(res=> res.json())
    .then(res2=>{
      console.log(res2)
      setJoke(res2.value.joke)
    })
  }

  useEffect(()=>{
    newJoke(fname, sname)
  },[fname, sname])
  return ( 
    <div>
     
      <h3>Samsung lover</h3>
      <input type="text" value={fname} onChange={(e)=>setfname(e.target.value)}></input>
      <input type="text" value={sname} onChange={(e)=>setsname(e.target.value)}></input>
      
      <button onClick={()=>newJoke(fname, sname)}>Get Another Joke</button>
      <h4>{joke}</h4>
    </div>
  );
}

export default App;

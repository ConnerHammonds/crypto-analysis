"use client";

export default function Home() {


  const payload = {
    addresses: [
    {
      address: "0x1E6E8695FAb3Eb382534915eA8d7Cc1D1994B152",
      networks: [
        "eth-mainnet",
        "base-mainnet",
        "matic-mainnet"
      ]
    }
  ],
    withMetadata: true,
    withPrices: true,
    includeNativeTokens: true,
    includeErc20Tokens: false,
    includeBlockMetadata: false
  };

  async function sendRequest() {
      const alchemyUrl = "https://api.g.alchemy.com/data/v1/{apiKey}/assets/tokens/by-address"
      const response = await fetch(alchemyUrl, {
        method: "POST",
        body: JSON.stringify(payload)
      });
      console.log(response);
    }

  return (
  <div>
  
  <h1>Simple prototype</h1>
  <p>Enter Wallet Address (the text box is directly below even though it's invisible :/)</p>
  
  <input className="Address" type="text"/>
  <button onClick={sendRequest}>Get Info</button> 
  </div>

  );
}

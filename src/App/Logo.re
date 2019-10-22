module Styles = {
  open Css;

  let root =
    style([
      cursor(`pointer),
      transformOrigin(`percent(50.0), `percent(50.0)),
      height(`percent(100.0)),
      marginLeft(Theme.Space.default),
      transform(`rotate(`deg(180.0))),
    ]);
};

[@react.component]
let make = (~onClick) => {
  <svg
    xmlns="http://www.w3.org/2000/svg"
    viewBox="0 0 774 875.7"
    className=Styles.root
    onClick={_ => onClick()}>
    <path fill="#FFF" d="M387 0l387 218.9v437.9L387 875.7 0 656.8V218.9z" />
    <path
      fill="#8ed6fb"
      d="M704.9 641.7L399.8 814.3V679.9l190.1-104.6 115 66.4zm20.9-18.9V261.9l-111.6 64.5v232l111.6 64.4zM67.9 641.7L373 814.3V679.9L182.8 575.3 67.9 641.7zM47 622.8V261.9l111.6 64.5v232L47 622.8zm13.1-384.3L373 61.5v129.9L172.5 301.7l-1.6.9-110.8-64.1zm652.6 0l-312.9-177v129.9l200.5 110.2 1.6.9 110.8-64z"
    />
    <path
      fill="#1c78c0"
      d="M373 649.3L185.4 546.1V341.8L373 450.1v199.2zm26.8 0l187.6-103.1V341.8L399.8 450.1v199.2zm-13.4-207zM198.1 318.2l188.3-103.5 188.3 103.5-188.3 108.7-188.3-108.7z"
    />
  </svg>;
};
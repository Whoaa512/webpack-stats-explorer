[@bs.config {jsx: 3}];

[@react.component]
let make = (~initialValue=0, ~children) => {
  let (currentValue, setValue) = React.useState(() => initialValue);
  let dec = state => state - 1;
  let inc = state => state + 1;
  let output = children(currentValue);

  <div>
    <button type_="button" onClick={_ => setValue(dec)}>
      {"-" |> React.string}
    </button>
    output
    <button type_="button" onClick={_ => setValue(inc)}>
      {"+" |> React.string}
    </button>
  </div>;
};
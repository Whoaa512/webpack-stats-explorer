type action =
  | Dec
  | Inc;

let reducer = (state, action) =>
  switch (action) {
  | Dec => state - 1
  | Inc => state + 1
  };

[@react.component]
let make = (~initialValue=0, ~children) => {
  let (state, send) = React.useReducer(reducer, initialValue);

  let dots = Array.make(state, React.string("."));
  <>
    <button type_="button" onClick=(_ => send(Dec))>
      ("-" |> React.string)
    </button>
    (children(state))
    <button type_="button" onClick=(_ => send(Inc))>
      ("+" |> React.string)
    </button>
    <pre> (dots |> React.array) </pre>
  </>;
};

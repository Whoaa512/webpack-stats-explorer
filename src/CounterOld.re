type action =
  | Dec
  | Inc;

let reducer = (action, state) =>
  switch (action) {
  | Dec => ReasonReact.Update(state - 1)
  | Inc => ReasonReact.Update(state + 1)
  };

let component = ReasonReact.reducerComponent("Counter");

let make = (~initialValue=0, children) => {
  ...component,
  initialState: () => initialValue,
  reducer,
  render: self => {
    let dots = Array.make(self.state, ReasonReact.string("."));
    <>
      <button type_="button" onClick={_ => self.send(Dec)}>
        {"-" |> ReasonReact.string}
      </button>
      {children(self.state)}
      <button type_="button" onClick={_ => self.send(Inc)}>
        {"+" |> ReasonReact.string}
      </button>
      <pre> ...dots </pre>
    </>;
  },
};
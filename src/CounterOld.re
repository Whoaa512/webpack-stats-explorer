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
    let dots = Array.make(self.state, React.string("."));
    <>
      <button type_="button" onClick=(_ => self.send(Dec))>
        ("-" |> React.string)
      </button>
      (children(self.state))
      <button type_="button" onClick=(_ => self.send(Inc))>
        ("+" |> React.string)
      </button>
      <pre> ...dots </pre>
    </>;
  },
};
/**
 * This is a wrapper created to let this component be used from the new React api.
 * Please convert this component to a [@react.component] function and then remove this wrapping code.
 */
let make =
  ReasonReactCompat.wrapReasonReactForReact(
    ~component,
    (
      reactProps: {
        .
        "initialValue": option('initialValue),
        "children": 'children,
      },
    ) =>
    make(~initialValue=?reactProps##initialValue, reactProps##children)
  );
[@bs.obj]
external makeProps:
  (~children: 'children, ~initialValue: 'initialValue=?, unit) =>
  {
    .
    "initialValue": option('initialValue),
    "children": 'children,
  } =
  "";

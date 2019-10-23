ReactDOMRe.renderToElementWithId(
  <CounterOld initialValue=32>
    ...{num =>
      " The world will end in "
      ++ string_of_int(num)
      ++ " years "
      |> ReasonReact.string
    }
  </CounterOld>,
  "app",
);
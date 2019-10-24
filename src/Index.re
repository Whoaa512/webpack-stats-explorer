[@bs.config {jsx: 3}];

ReactDOMRe.renderToElementWithId(
  <CounterOld initialValue=32>
    {num =>
       " The world will end in "
       ++ string_of_int(num)
       ++ " years "
       |> React.string}
  </CounterOld>,
  "app",
);
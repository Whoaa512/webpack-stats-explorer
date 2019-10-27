ReactDOMRe.renderToElementWithId(
  <Counter initialValue=32>
    {num =>
       " The world will end in "
       ++ string_of_int(num)
       ++ " years "
       |> React.string}
  </Counter>,
  "app",
);
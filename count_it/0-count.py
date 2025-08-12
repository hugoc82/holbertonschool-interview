#!/usr/bin/env python3
"""Count keywords in titles of 'hot' posts from a subreddit (recursively)."""

from typing import Dict, Iterable, Optional
import requests
import sys


def count_words(subreddit: str,
                word_list: Iterable[str],
                after: Optional[str] = None,
                counts: Optional[Dict[str, int]] = None,
                multiplicity: Optional[Dict[str, int]] = None) -> None:
    """Query Reddit API and print sorted counts of `word_list` in hot titles."""
    if counts is None:
        counts = {}
    if multiplicity is None:
        multiplicity = {}
        for w in word_list:
            key = str(w).lower()
            multiplicity[key] = multiplicity.get(key, 0) + 1
            if key not in counts:
                counts[key] = 0

    url = f"https://www.reddit.com/r/{subreddit}/hot.json"
    params = {"limit": 100}
    if after:
        params["after"] = after

    headers = {
        "User-Agent": "holberton_count_it:1.0 (by u/learning-bot)"
    }

    try:
        resp = requests.get(
            url, headers=headers, params=params, timeout=10,
            allow_redirects=False
        )
    except requests.RequestException:
        return

    if resp.status_code != 200:
        return

    data = resp.json().get("data", {})
    children = data.get("children", [])

    for post in children:
        title = post.get("data", {}).get("title", "")
        for token in title.lower().split():
            if token in counts:
                counts[token] += 1

    next_after = data.get("after")
    if next_after:
        count_words(subreddit, word_list, next_after, counts, multiplicity)
        return

    final_counts: Dict[str, int] = {}
    for word, cnt in counts.items():
        mult = multiplicity.get(word, 0)
        total = cnt * mult
        if total > 0:
            final_counts[word] = total

    if not final_counts:
        return

    ordered = sorted(final_counts.items(),
                     key=lambda kv: (-kv[1], kv[0]))

    for word, total in ordered:
        print(f"{word}: {total}")


if __name__ == "__main__":
    if len(sys.argv) < 3:
        print(f"Usage: {sys.argv[0]} <subreddit> <list of keywords>")
        print(f"Ex: {sys.argv[0]} programming 'python java javascript'")
    else:
        count_words(sys.argv[1], [x for x in sys.argv[2].split()])
